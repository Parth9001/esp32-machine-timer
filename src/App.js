import "./App.css";
import CountdownTimer from "./Components/Countdown Timer/CountdownTimer";
import Header from "./Components/Page/Header";
import WebSocket from "websocket";

function App() {
  const [timeTaken, setTimeTaken] = useState(0);

  useEffect(() => {
    const ws = new WebSocket("ws://esp32-ip-address:80"); // Replace with your ESP32 IP address
    ws.onopen = () => {
      console.log("WebSocket connection opened");
    };

    ws.onmessage = (event) => {
      const data = event.data;
      console.log("Received data from ESP32:", data);
      // Update your React state with the received data
      setTimeTaken(data);
    };

    return () => {
      ws.close(); // Close the WebSocket connection when the component unmounts
    };
  }, []);

  let timer = Date.now() + timeTaken * 1000 * 60;
  return (
    <div className="App">
      <Header />
      <CountdownTimer countdownTimestampMs={timer} />
    </div>
  );
}

export default App;
