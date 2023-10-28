import "./App.css";
import CountdownTimer from "./Components/Countdown Timer/CountdownTimer";
import Header from "./Components/Page/Header";
import WebSocket from "websocket";

function App() {
  const [timeTaken, setTimeTaken] = useState(0);

  let timer = Date.now() + timeTaken * 1000 * 60;
  return (
    <div className="App">
      <Header />
      <CountdownTimer countdownTimestampMs={timer} />
    </div>
  );
}

export default App;
