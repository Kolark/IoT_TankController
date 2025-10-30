from flask import Flask, request
from flask_socketio import SocketIO, emit
import sys

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*", async_mode='threading', transports=['websocket'])

connected_clients = set()

@socketio.on('connect')
def handle_connect():
    connected_clients.add(request.sid)
    print(f"Client connected: {request.sid}", flush=True)

@socketio.on('disconnect')
def handle_disconnect():
    connected_clients.discard(request.sid)
    print(f"Client disconnected: {request.sid}", flush=True)

@socketio.on('message')
def handle_message(data):
    print(f"Received: {data}", flush=True)
    emit('response', f"Server received: {data}")

@app.route('/notify', methods=['POST'])
def notify():
    message = request.json.get('message', 'Notification from endpoint')
    for client_id in connected_clients:
        socketio.emit('notification', message, to=client_id)
    return {'status': 'sent', 'clients': len(connected_clients)}

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, allow_unsafe_werkzeug=True)