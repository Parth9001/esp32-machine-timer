import React, { useState, useEffect } from "react";
import './CountdownTimer.css'
import {getRemainingTime} from './Utils/CountdownTimerUtils'



const CountdownTimer = ({countdownTimestampMs}) => {
    const defaultRemainingTime = getRemainingTime(countdownTimestampMs);
    // const defaultRemainingTime = {
    //     seconds : 0,
    //     minutes : 0
    // }

    const [remainingTime, setRemainingTime] = useState(defaultRemainingTime);
    
    useEffect(() => {
        const intervalId = setInterval(() => {
            updateRemainingTime(countdownTimestampMs);
        }, 1000);
        return () => clearInterval(intervalId);
    }, [countdownTimestampMs])

    function updateRemainingTime(countDown){
        setRemainingTime(getRemainingTime(countDown));
    }

    return(
        <div>
            <div className="countdownTimer">
                {/* <span>{remainingTime.days}</span>
                <span>days</span>
                <span>{remainingTime.hours}</span>
                <span>hours</span> */}
                <span>{remainingTime.minutes}</span>
                <span>minutes</span>
                <span>{remainingTime.seconds}</span>
                <span>seconds</span>
            </div>
        </div>
    );
}
export default CountdownTimer; 