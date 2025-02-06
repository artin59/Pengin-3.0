import React from "react";
import { useAuth0 } from "@auth0/auth0-react";
import Coach from "../Pages/Coach"
import Player from "../Pages/Player"
import Doctor from "../Pages/Doctor"



const Profile = () => {
  const { user, isAuthenticated, isLoading } = useAuth0();

  if (isLoading) {
    return <div>Loading ...</div>;
  }
  

  return (
    user !== undefined && isAuthenticated && (
        <div>
            
            {(() => {

                switch(user.name){

                    case "artinkiany59@gmail.com":
                        return <Coach/>
                    case "l9ligma@gmail.com":
                        return <Player/>
                    case "artin59@my.yorku.ca":
                        return <Doctor/>
                    default:
                        return <h1>Not in Records</h1>
                }

            })()}
    </div>
    )
  );
};

export default Profile;