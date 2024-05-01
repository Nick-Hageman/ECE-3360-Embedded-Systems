import websocket
import time
import json

def on_message(ws, message):
    print("Received from server: %s" % message)

def on_error(ws, error):
    print("Error: %s" % error)

def on_close(ws):
    print("### Connection closed ###")

def on_open(ws):
    def run(*args):
        for i in range(10):  # Send 10 messages
            # Simulate sending different inputs; these could be JSON-encoded strings
            input_data = json.dumps({'button': 'A', 'state': 'pressed', 'intensity': i})
            print("Sending: %s" % input_data)
            ws.send(input_data)
            time.sleep(1)  # Wait for 1 second between sends
        
        time.sleep(1)
        ws.close()
        print("Thread terminating...")
    
    # Run the sending function in a thread if necessary
    import threading
    thread = threading.Thread(target=run)
    thread.start()

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws_url = "ws://172.23.5.70:8080" # 8080 for pi, 3000 for personal laptop
    # ws_url = "ws://localhost:3000"
    ws = websocket.WebSocketApp(ws_url,
                                on_message=on_message,
                                on_error=on_error,
                                on_close=on_close)
    ws.on_open = on_open
    ws.run_forever()
