import { useLocalStorage } from "../Utils/useLocalStorage"
import { useState } from "react"
import Player from "./Player"
import "./Coach.css"

const Coach = () => {


  const [show, setShow] = useState(false);
  //const [note, showNote] = useState('');

  const {getItem} = useLocalStorage("note");


  const showPlayer = () => {
    if (show)
      setShow(false);
    else
      setShow(true);
  }

  return (

    <div className="Coach">

      <h1>Coach</h1>
      <h2>Pick a player</h2>
      <button className="playerNameBtn" onClick={showPlayer}> L9 Ligma </button>
      {show && (<Player/>)}
      <button className="submitBtn" onClick={()=> console.log(getItem())}>Get Doctor's Note</button>

    </div>



  )



}

export default Coach