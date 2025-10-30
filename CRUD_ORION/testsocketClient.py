import socketio
import time

sio = socketio.Client()

@sio.on('response')
def handle_response(data):
    print(f"Server says: {data}")

@sio.on('notification')
def handle_notification(data):
    print(f"Notification: {data}")

sio.connect('http://52.87.197.74:5000')

sio.emit('message', 'First message')
time.sleep(2)
sio.emit('message', 'Second message')

input("Press Enter to disconnect...")
sio.disconnect()