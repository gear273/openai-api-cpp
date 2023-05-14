import json
import os
import sys

import requests
import tiktoken
from dotenv import load_dotenv

load_dotenv()


def get_token_count(encoding_name: str, messages: list[dict[str, str]]) -> int:
    """Returns the number of tokens in a text string."""
    encoding = tiktoken.get_encoding(encoding_name)
    total_tokens = 0

    for message in messages:
        if "content" in message:
            string = message["content"]
            total_tokens += len(encoding.encode(string))

    return total_tokens


class OpenAI:
    def __init__(self, api_key):
        self.api_key = api_key
        self.headers = {
            "Authorization": f"Bearer {self.api_key}",
            "Content-Type": "application/json",
        }
        self.chat_completions_url = "https://api.openai.com/v1/chat/completions"

    def stream_chat_completions(
        self,
        messages,
        model="gpt-3.5-turbo",
        max_tokens=512,
        temperature=0.7,
    ):
        data = {
            "model": model,
            "max_tokens": max_tokens,
            "temperature": temperature,
            "stream": True,  # Enable streaming
            "messages": messages,
        }
        response = requests.post(
            self.chat_completions_url, headers=self.headers, json=data, stream=True
        )

        if response.status_code == 200:
            message = ""
            for line in response.iter_lines():
                # If the line is not empty
                if line:
                    # Decode it to string
                    line = line.decode("utf-8")

                    # Check if the line starts with 'data: '
                    if line.startswith("data: "):
                        # If it does, strip it out
                        line = line[6:]

                    # If the line is '[DONE]', stop processing
                    if line == "[DONE]":
                        break

                    json_line = json.loads(line)

                    try:
                        token = json_line["choices"][0]["delta"]["content"]
                        if token:
                            message += token
                            print(token, end="")
                            sys.stdout.flush()
                    except (KeyError,):
                        continue

            # Return the assistant's message after the loop
            return {"role": "assistant", "content": message}
        else:
            print(f"Error: {response.status_code}")
            print(f"Error message: {response.text}")
            return None  # Return None in case of an error


def main():
    # Usage
    model = "gpt-3.5-turbo"
    api_key = os.getenv("OPENAI_API_KEY")
    openai = OpenAI(api_key)

    # Initialize the conversation with a system message
    messages = [
        {
            "role": "system",
            "content": "Your name is GPT. You are a helpful assistant.",
        }
    ]

    while True:
        try:
            # Ask the user for their message
            user_message = input("\nYou: ")
        except (
            KeyboardInterrupt,
            EOFError,
        ):
            exit()

        if user_message == "quit":
            exit()

        # Add the user message to the conversation
        messages.append({"role": "user", "content": user_message})

        print("\nGPT:", end=" ")

        # Call the streaming API
        assistant_message = openai.stream_chat_completions(messages)

        # If the function returned a message, add it to the conversation
        if assistant_message is not None:
            messages.append(assistant_message)

        print()  # output a newline character

        encoding = tiktoken.encoding_for_model(model)
        token_count = get_token_count(encoding.name, messages=messages)
        print(f"Consumed {token_count} tokens.")


if __name__ == "__main__":
    main()
