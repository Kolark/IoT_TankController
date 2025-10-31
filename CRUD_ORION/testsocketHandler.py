from flask import Flask, render_template, jsonify, redirect, url_for, session, request
from functools import wraps
import asyncio
import websockets
import json
import threading
import sys
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
connected_clients = set()

async def handle_client(websocket, path):
    connected_clients.add(websocket)
    print(f"Client connected: {id(websocket)}", flush=True)

    try:
        async for message in websocket:
            print(f"Received: {message}", flush=True)

            try:
                data = json.loads(message)
                if isinstance(data, dict) and 'type' in data:
                    if data['type'] == 'message':
                        response = json.dumps({'type': 'response', 'data': f"Server received: {data.get('data', '')}"})
                        await websocket.send(response)
            except:
                pass

    except websockets.exceptions.ConnectionClosed:
        pass
    finally:
        connected_clients.discard(websocket)
        print(f"Client disconnected: {id(websocket)}", flush=True)

async def broadcast_notification(message):
    if connected_clients:
        notification = json.dumps({'type': 'notification', 'data': message})
        await asyncio.gather(*[client.send(notification) for client in connected_clients], return_exceptions=True)

def run_websocket_server():
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    start_server = websockets.serve(handle_client, '0.0.0.0', 5001)
    loop.run_until_complete(start_server)
    loop.run_forever()

@app.route('/notify', methods=['POST'])
def notify():
    message = request.json.get('message', 'Notification from endpoint')

    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(broadcast_notification(message))
    loop.close()

    return jsonify({'status': 'sent', 'clients': len(connected_clients)})


def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        print("checking login...")
        return f(*args, **kwargs)
    return decorated_function

if __name__ == '__main__':
    ws_thread = threading.Thread(target=run_websocket_server, daemon=True)
    ws_thread.start()

    app.run(host='0.0.0.0', port=5000)