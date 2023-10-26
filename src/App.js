import './App.css';
import CountdownTimer  from './Components/Countdown Timer/CountdownTimer';
import Header from './Components/Page/Header'

function App() {
  return (
    <div className="App">
        <Header/>
        <CountdownTimer
        countdownTimestampMs={timer}/>
      </div>
  );
}

export default App;
