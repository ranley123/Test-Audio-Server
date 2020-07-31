import socket
import os
import wave
import argparse
import sys

def get_args(args=sys.argv[1:]):
    parser = argparse.ArgumentParser(description="Parses command.")
    parser.add_argument('-p', '--port')
    args = parser.parse_args(args)
    return args

def recv_audio(client):
    frames = []
    spliter = 'EOF'.encode('utf-8')

    while(True):
        temp = client.recv(1024)
        if spliter in temp:
            temp = temp.split(spliter)[0]
            print('audio end')
            frames.append(temp)
            break
        else:
            frames.append(temp)
    return frames

def save_to_wav_file(filename, frames):
    wf = wave.open(filename, "wb")
    wf.setnchannels(1)
    wf.setsampwidth(2)
    wf.setframerate(32000)
    wf.writeframes(b''.join(frames))
    wf.close()

def on_test_audio(client):
    frames = recv_audio(client)
    save_to_wav_file('test.wav', frames)

def connect():
    args = get_args()
    port = int(args.port)
    print("starting...")
    host = "0.0.0.0"

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(10)

    while True:
        print('waiting for new connection...')
        client, address = server.accept()
        print('new connection: ', address[0], ': ', address[1])

        while True:
            on_test_audio(client)

if __name__ == "__main__":
    connect()