#/usr/bin/env bash

repo_root=`dirname $0`
if [[ repo_root != '.' ]]; then 
	cd $repo_root
fi

echo "Enter picture path: (default \"`pwd`/brightness_icon.png\")"
read y
if [[ $y == "" ]]; then 
	sed -i "s#^PICTURE_PATH = .*#PICTURE_PATH = \"`pwd`/brightness_icon.png\"#" ./release.py
else
	sed -i "s#^PICTURE_PATH = .*#PICTURE_PATH = \"$y\"#" ./release.py
fi
printf "\033[0;32mPicture path set\n\033[0m"

if [[ ! -e "/sys/class/backlight/intel_backlight/max_brightness" || 
	  ! -e "/sys/class/backlight/intel_backlight/brightness" ]]; then 
	echo "Backlight files doesn't exist in the default path. Please enter yours"
	read -p 'max brightness file path: ' max_path
	read -p 'cur brightness file path: ' cur_path
	sed -i "s#^MAX_BRIGHTNESS_PATH = .*#MAX_BRIGHTNESS_PATH = \"${max_path}\"#" ./release.py
	sed -i "s#^BRIGHTNESS_PATH = .*#BRIGHTNESS_PATH = \"${cur_path}\"#" ./release.py
	echo Modified successfully!
	printf "\033[0;32mBacklight file set\n\033[0m"
elif [[ ! -r "/sys/class/backlight/intel_backlight/max_brightness" || 
	  ! -r "/sys/class/backlight/intel_backlight/brightness" ]]; then 
	printf "\033[0;31mCannot read files.\n\033[0m"
	echo "Please add read permission to "
	echo "/sys/class/backlight/intel_backlight/max_brightnes"
	echo "/sys/class/backlight/intel_backlight/brightnes"
	exit 1
else
	printf "\033[0;32mBacklight file ok\n\033[0m"
fi


echo "Please edit your shortcut with command:"
echo -e \"python `pwd`/release.py inc\" for increase brightness
echo -e \"python `pwd`/release.py dec\" for decrease brightness 

echo -e "\nRun \"lxqt-config-globalkeyshortcuts\" to open shortcut configuration" 

			
			


