# iLO Research Documentation

Setting up iLO:

https://www.youtube.com/watch?v=5KcDefkJP8s (Skip the first 10ish minutes)

iLO WebUI Interface:

https://www.youtube.com/watch?v=GuH9d-UQa2k (The last 3ish minutes are just OS stuff, skip it)



#Getting Hewlett Packard Enterprise iLO up
--
1. Boot up the server and hit (F10) for the Intelligent Provisioning page when available. 
1. Go to system configuration > Network controllers
1. On the iLO interface and the primary interface for the server, record the MAC Address of the iLO interface.
1. Give the MAC Address of the iLO interface and the primary interface to Lynne (SOE IT Manager) so that their DHCP server can reserve the IP for the device to be able to connect with the domain name. 
1. After the DHCP reservation has been set, physically unplug and replug in the power to reset the iLO network address. 
1. On a computer connected to Eduroam/Cruznet, ping the assigned address and point the web browser to the iLO to see if the iLO is connected with the campus network. 
1. Log in with the default login to each of the iLO with the supplied administrator login and password on the box. 
