import base64


def main():
    
    while True:
        command = input("encode?")
        text = input("encoded text: ")
        if command == "encode":
            ascii_text = text.encode('ascii')
            encoded = base64.b64encode(ascii_text)
            print(encoded)
        elif command == 'q':
            break
        else:
            print('Incorrect command')

if __name__ == "__main__":
    main()