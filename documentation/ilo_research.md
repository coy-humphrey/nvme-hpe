# iLO Research Documentation
#Getting Hewlett Packard Enterprise iLO up
--
1. Boot up the server and hit (F10) for the Intelligent Provisioning page when available. 
1. Go to system configuration > Network controllers
1. On the iLO interface and the primary interface for the server, record the MAC Address of the iLO interface.
1. Give the MAC Address of the iLO interface and the primary interface to Lynne (SOE IT Manager) so that their DHCP server can reserve the IP for the device to be able to connect with the domain name. 
1. After the DHCP reservation has been set, physically unplug and replug in the power to reset the iLO network address. 
1. On a computer connected to Eduroam/Cruznet, ping the assigned address and point the web browser to the iLO to see if the iLO is connected with the campus network. 
1. Log in with the default login to each of the iLO with the supplied administrator login and password on the box. 
1. 

#Partitioning the RAID drives
--
1. In the BIOS landing page, boot to the "Intelligent Provisioning" boot menu. 
1. Go to "HP Smart Storage Administrator (SSA)"
1. Under the Configure panel (located on the right of the screen, select the primary Smart Array Controller and select "Configure" on the page
1. In the primary array controller configure page, select "Create Array"
1. Follow the onscreen steps and when selecting the drives, select drives 1 and 2 and use the standard partitioning (RAID1). 
1. Do steps 3 to 5 again for drives 3 and 4. 



#Installing CentOS onto the server
--
1. Download the entire CentOS 7 installation iso. It should be the "Everything Iso" (7+ GB)
1. Connect to the iLO landing page and login with an account that has remote console access.
1. Launch the remote console. For Windows, use the .NET framework. For Mac or Linux, use the Java applet. 
1. In the remote console, load the CentOS 7 iso.
1. Reboot the server and hit (F11) to go to the boot menu and select the iLO iso drive.
1. In Cent OS 7 installation, select English as language and English (US) as keyboard. 
1. When setting the time, change the time zone to "Los Angeles" and connect to NTP for time and click done. 
1. Go to the network page and switch the wired network interface to on. 
1. In the packages, select Minimum configuration with the following packages **<--**
1. In the drives, select the primary partition (drives 1 and 2) to install CentOS.
1. Begin installation after settings has been set and set a Root password. 
