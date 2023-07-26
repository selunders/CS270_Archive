#! /bin/bash

# Seth Lunders | V00554272
# Professor Rinker
# CS 270
# Feb 28 2021
# Assignment 3
# ------------


# Get folder name 
input1=$1;
# Remove file extension
input1Min=${input1%.*};
# Add .tmp extension
tempFolder="$input1Min.tmp";

# Check for existing temporary folder
if [ -e $tempFolder ]; then
    echo $tempFolder exists
    echo Renaming $tempFolder to $tempFolder.bak
    mv $tempFolder $tempFolder.bak
fi

# Create temporary folder
mkdir $tempFolder

# Loop through each input file, copying each to the tmp folder
i=1;
for fileName in "$@"
do
    # Check if file exists already in the folder (copying the same file twice)
    if [ -f $tempFolder/$fileName ]; then
        echo "$fileName already exists in $tempFolder, what would you like to do?"
        cat << ENDOFMENU
    1: Overwrite
    2: Don't Copy
    3: Rename
ENDOFMENU
        echo -n 'Which option? '
        read reply
        echo
        case $reply in
        "1")
            cp $fileName $tempFolder || echo "Unable to copy $fileName"
            i=$((i + 1));
            ;;
        "2")
            echo "Skipping $fileName"
            i=$((i + 1));
            ;;
        "3")
            echo "What would you like to rename the file to?"
            read newName
            cp $fileName $tempFolder/$newName || echo "Unable to copy $fileName"
            i=$((i + 1));
            ;;
        *)
            echo Illegal choice, skipping
            ;;
        esac
else
    cp $fileName $tempFolder || echo "Could not copy $fileName into $tempFolder";
    i=$((i + 1));
fi
done

# Archive folder
echo Archiving files...
tar -cf $input1Min.tar $tempFolder/

# Delete temporary folder
rm -r $tempFolder

# If a folder existed and was renamed, rename it back to its original name
if [ -e $tempFolder.bak ]; then
    mv -T $tempFolder.bak $tempFolder
fi

echo "Archive completed."