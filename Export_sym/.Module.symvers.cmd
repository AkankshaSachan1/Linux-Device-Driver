cmd_/home/cdac-admin/Desktop/Saurabh_DeviceDriver/DeviceDriver_Day1/Export_sym/Module.symvers := sed 's/\.ko$$/\.o/' /home/cdac-admin/Desktop/Saurabh_DeviceDriver/DeviceDriver_Day1/Export_sym/modules.order | scripts/mod/modpost -m -a  -o /home/cdac-admin/Desktop/Saurabh_DeviceDriver/DeviceDriver_Day1/Export_sym/Module.symvers -e -i Module.symvers   -T -