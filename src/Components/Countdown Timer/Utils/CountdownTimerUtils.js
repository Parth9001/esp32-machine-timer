// import dayjs from 'daysjs';

export function getRemainingTime(timestampMs){
    const timeDiff = (timestampMs - Date.now());
    console.log(timeDiff);
    const sec = Math.floor((timeDiff/1000)%60);
    const min = Math.floor((timeDiff/60000)%60);
    // const hour = Math.floor((timeDiff/3600000)%24);
    if(timeDiff<=0){
        return{
            seconds : 0,
            minutes: 0,
            // hours : 0
        }
    }
    return{
        seconds : sec,
        minutes: min,
        // hours : hour
    }
}