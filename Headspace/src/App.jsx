import { useState } from 'react'
import LoginButton from "./Components/LoginButton"
import LogoutButton from "./Components/LogoutButton"
import Profile from "./Components/Profile"
import './App.css'

function App() {

  return (

    <main className='column'>

      <h1>Auth0 Login</h1>
      <LoginButton/>
      <LogoutButton/>
      <Profile />
    </main>
  )
}

export default App
