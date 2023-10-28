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
  let updated_time;

  useEffect(() => {
    fetch("http://127.0.0.1:8000/timer/1")
      .then((response) => {
        if (!response.ok) {
          throw new Error("Network response was not ok");
        }
        return response.json();
      })
      .then((data) => {
        console.log(data.timer);
        let timeTaken = data.timer;
        updated_time = data.updated_time;
        console.log(updated_time);
        setTimer(timer + timeTaken * 1000 * 60);
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
