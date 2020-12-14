# Remote Switch
This project allows users (clients) to control their switches remotely through cloud (AWS EC2).

### System architecture
<img src="./media/system-architecture.png" width="80%" height="80%">

### Wiring diagram
<img src="./media/wiring-diagram.png" width="80%" height="80%"> \
We use **left LED to represent the lamp** that we used in the project and take **right LED as a Wi-Fi signal indicator**. \
*(Note: The parts in the wiring diagram are not exactly the same as the parts that we used in the project.)*

# Test Environment
+ AWS EC2 - Ubuntu Server 18.04 LTS (HVM), SSD Volume Type
+ Node.js 13.5.0 (with npm 6.13.4 installed)
+ NodeMCU v2 (with ESP8266)
+ Relay module: JQC-3FF-S-Z

# [Package Requirements](./requirements.bat)
+ express==4.17.1 (for Node.js)
+ ESP8266WiFi (for NodeMCU)

# License
This project is under the [MIT License](./LICENSE).
