// import "./App.css";
// import CountdownTimer from "./Components/Countdown Timer/CountdownTimer";
// import Header from "./Components/Page/Header";

// function App() {
//   let timer = Date.now();
//   fetch("http://127.0.0.1:8000/timer/1")
//     .then((response) => {
//       if (!response.ok) {
//         throw new Error("Network response was not ok");
//       }
//       return response.json();
//     })
//     .then((data) => {
//       console.log(data.timer);
//       let timeTaken = data.timer;
//       timer += timeTaken * 1000 * 60;
//     })
//     .catch((error) => {
//       console.error("There was a problem with the fetch operation:", error);
//     });

//   return (
//     <div className="App">
//       <Header />
//       <CountdownTimer countdownTimestampMs={timer} />
//     </div>
//   );
// }

// export default App;
import React, { useEffect, useState } from "react";
import "./App.css";
import CountdownTimer from "./Components/Countdown Timer/CountdownTimer";
import Header from "./Components/Page/Header";

function App() {
  const [timer, setTimer] = useState(Date.now());
  const [initTime, setInitTime] = useState(Date.now());
  let updated_time;

  useEffect(() => {
    fetch("http://192.168.0.111:8000/timer/1")
      .then((response) => {
        if (!response.ok) {
          throw new Error("Network response was not ok");
        }
        return response.json();
      })
      .then((data) => {
        console.log(data.timer);
        let timeTaken = data.timer;
        const weird_time = data.updated_time;
        const date = new Date(weird_time);
        updated_time = date.getTime();
        console.log(updated_time);
        setTimer(updated_time + timeTaken * 1000 * 60);
      })
      .catch((error) => {
        console.error("There was a problem with the fetch operation:", error);
      });
  }, []); // Empty dependency array, runs the effect once on mount

  return (
    <div className="App">
      <Header />
      <CountdownTimer countdownTimestampMs={timer} />
    </div>
  );
}

export default App;
