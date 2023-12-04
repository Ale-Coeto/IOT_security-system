# IOT_security-system
Security system prototype for the elder. Access to the house is granted through face recognition and several sensors monitor house conditions. All information is displayed through a web aplication.

## Web App
### Features
- Authentication: Users register or login using GoogleOAuth
- Dashboard: Main page to see sensor values and last person detected at the door
- Logs: Logs from people who have been detected, displaying time, image and name if recognized
- Devices: Available devices connected to the same network
- Access: Subpage to add or edit people who are authorized of entering the house

## Face Recognition API
An API was developed using Flask and face-recognition to recieve images and return if detected, the name of the person recognized.
The API was hosted on an AWS EC2 instance, through Docker.
The detected image was decoded from base64 and the other images were requested from the sent URLs.

## NodeMCU
For instant communication, AWS Websocket API Gateway was used, establishing several routes and connections to the backend.

</br>

# Infrastructure and tech stack
<img width="full" alt="Infrastructure" src="https://github.com/Ale-Coeto/IOT_security-system/assets/109093534/340b8216-f14c-440c-bfd7-1e201a357577">

# Check it out
- [Demo](https://youtu.be/4bw-oJFjs5E)
- [Webapp](iot-security-system.vercel.app)
  
_Database may be down after some time_
