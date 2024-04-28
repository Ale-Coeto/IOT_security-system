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
The API was hosted on an AWS EC2 instance, using Docker.
The detected image was decoded from base64 and the other images were requested from the sent URLs.

## NodeMCU
For instant communication, AWS Websocket API Gateway was used, establishing several routes and connections to the backend.

</br>

# Infrastructure 
<img width="full" alt="Infrastructure" src="https://github.com/Ale-Coeto/IOT_security-system/assets/109093534/340b8216-f14c-440c-bfd7-1e201a357577">

</br>

## Tech stack
| Web App | Face Recognition API | Backend |
| ------------- | ------------- | ------------- |
| Typescript | AWS EC2 | AWS Websocket API Gateway |
| React | AWS ELB | Nodejs |
| Nextjs | Docker | Planet Scale (SQL) |
| Prisma | Python| MQTT  |
| Tailwind | Flask  | Node-red |
| Cloudinary | Face-recognition  | Google OAuth |
|  |   | tRPC |



</br>

# Check it out
- [Webapp](https://iot-security-system.vercel.app)
- [Demo video](https://youtu.be/4bw-oJFjs5E)
- [Poster](https://drive.google.com/file/d/1fKxKSY9jASYbpcnpqm5yKVu9zmmycmgy/view?usp=sharing)
- [Report](https://drive.google.com/file/d/1k9zNSgABw7f5123p5nHLYBX5CJaQDszs/view?usp=sharing)
  
_Database may be down after some time_

</br>

# Development team

| Name                  | Github     |
| --------------------- | --------- |
| Roberto Gómez | |
| Diego Govea | |
| Juan Félix | |
| Claudia Tobias | |
| Alejandra Coeto | [@Ale-Coeto](https://github.com/Ale-Coeto) | 

