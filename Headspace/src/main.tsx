import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { Auth0Provider } from '@auth0/auth0-react';
import './index.css'
import App from './App.tsx'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
<Auth0Provider
    domain="dev-lbhjucs031bg6ksr.us.auth0.com"
    clientId="mZ2HyPVIGoSc02d3KmUOb2U5rFi2jV82"
    authorizationParams={{
      redirect_uri: window.location.origin
    }}
  >
    <App />
  </Auth0Provider>
  </StrictMode>
)
