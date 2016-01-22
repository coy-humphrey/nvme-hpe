# Server Setup Documentation

Installing CentOS, stuff like that...
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
