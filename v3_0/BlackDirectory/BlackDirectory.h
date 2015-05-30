 /*

 ####################################################################################
 #  BlackLib Library controls Beaglebone Black's inputs and outputs.                #
 #  Copyright (C) 2013-2015 by Yigit YUCE                                           #
 ####################################################################################
 #                                                                                  #
 #  This file is part of BlackLib library.                                          #
 #                                                                                  #
 #  BlackLib library is free software: you can redistribute it and/or modify        #
 #  it under the terms of the GNU Lesser General Public License as published by     #
 #  the Free Software Foundation, either version 3 of the License, or               #
 #  (at your option) any later version.                                             #
 #                                                                                  #
 #  BlackLib library is distributed in the hope that it will be useful,             #
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of                  #
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   #
 #  GNU Lesser General Public License for more details.                             #
 #                                                                                  #
 #  You should have received a copy of the GNU Lesser General Public License        #
 #  along with this program.  If not, see <http://www.gnu.org/licenses/>.           #
 #                                                                                  #
 #  For any comment or suggestion please contact the creator of BlackLib Library    #
 #  at ygtyce@gmail.com                                                             #
 #                                                                                  #
 ####################################################################################

 */



#ifndef BLACKDIRECTORY_H_
#define BLACKDIRECTORY_H_

#include <string>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <cstdio>
#include <algorithm>





namespace BlackLib
{
    const std::string CURRENT_DIRECTORY_NOT_FOUND = "Current Directory Couldn\'t Find"; //!< If current directory could not find, function returns this


    // ########################################### BLACKDIRECTORY DECLARATION STARTS ############################################ //

    /*! @brief Interacts with end user, to use directory system of Linux based OS.
     *
     *    This class is end node to use directory system. End users interact with
     *    the directories from this class. It includes public functions for managing
     *    directories.
     *
     * @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         myDirectoryProject
         |-> src
             |-> BlackLib
                 |-> BlackDirectory
                     |-> BlackDirectory.cpp
                     |-> BlackDirectory.h
                 |-> BlackThread
                     |-> BlackThread.cpp
                     |-> BlackThread.h
                 |-> BlackMutex
                     |-> BlackMutex.cpp
                     |-> BlackMutex.h
                 |-> BlackTime
                     |-> BlackTime.cpp
                     |-> BlackTime.h
                 |-> BlackADC
                     |-> BlackADC.cpp
                     |-> BlackADC.h
                 |-> BlackGPIO
                     |-> BlackGPIO.cpp
                     |-> BlackGPIO.h
                 |-> BlackI2C
                     |-> BlackI2C.cpp
                     |-> BlackI2C.h
                 |-> BlackPWM
                     |-> BlackPWM.cpp
                     |-> BlackPWM.h
                 |-> BlackSPI
                     |-> BlackSPI.cpp
                     |-> BlackSPI.h
                 |-> BlackUART
                     |-> BlackUART.cpp
                     |-> BlackUART.h
                 |-> BlackCore.cpp
                 |-> BlackCore.h
                 |-> BlackDef.h
                 |-> BlackErr.h
                 |-> BlackLib.h
             |-> myDirectoryProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackDirectory.h or another source files with adding this line to your project file (myDirectoryProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackDirectory/BlackDirectory.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (myDirectoryProject.cpp at the
     *  example), you have to include BlackDirectory.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackDirectory/BlackDirectory.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: myDirectoryProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackDirectory/BlackDirectory.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackDirectory  myDir("/home/root");
     *      std::cout << myDir.getApplicationDirectoryPath();
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: myDirectoryProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackDirectory/BlackDirectory.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackDirectory  myDir("/home/root");
     *      std::cout << myDir.getApplicationDirectoryPath();
     *
     *      return 0;
     *  }
     * @endcode
     *
     */
    class BlackDirectory
    {
        private:
            std::string  applicationDirectory;                  /*!< @brief is used to hold the application directory */


        public:

            /*!
             * This enum is used to define hidden files showing format.
             */
            enum hiddenFormat
            {
                ExcludeHiddens = 0,                             /*!< enumeration for @a excluding hidden files from output */
                IncludeHiddens = 1                              /*!< enumeration for @a including hidden files from output */
            };

            /*!
             * This enum is used to define directory components showing format.
             */
            enum componentFormat
            {
                Directory    = 1,                               /*!< enumeration for showing @a directories at the output */
                File         = 2,                               /*!< enumeration for showing @a files at the output */
                SymbolicLink = 4,                               /*!< enumeration for showing @a symbolic @a links at the output */
                All          = Directory|File|SymbolicLink      /*!< enumeration for showing @a all type components at the output */
            };


            /*! @brief Constructor of BlackDirectory class.
            *
            * This function initializes application path.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir();
            *   BlackLib::BlackDirectory *myDirPtr = new BlackLib::BlackDirectory();
            *
            *   std::cout << myDir.getApplicationDirectoryPath() << std::endl;
            *   std::cout << myDirPtr->getApplicationDirectoryPath();
            * @endcode
            *
            * @sa getCurrentDirectoryPath()
            */
            BlackDirectory();

            /*! @brief Constructor of BlackDirectory class.
            *
            * This function initializes application path and changes directory(cd).
            *
            * @param [in] path    destination directory name
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/home/root");
            *   BlackLib::BlackDirectory *myDirPtr = new BlackLib::BlackDirectory("/home/root");
            *
            *   std::cout << myDir.getApplicationDirectoryPath() << std::endl;
            *   std::cout << myDirPtr->getApplicationDirectoryPath();
            * @endcode
            *
            * @sa getCurrentDirectoryPath()
            * @sa cd()
            */
            BlackDirectory(std::string path);

            /*! @brief Destructor of BlackDirectory class.
            *
            */
            virtual ~BlackDirectory();

            /*! @brief Exports "home" directory path.
            *
            *  @return User specific "home" directory path or empty string.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir();
            *
            *   std::cout << "My home dir: " << myDir.getHomeDirectoryPath() << std::endl;
            *   std::cout << "My home dir: " << BlackLib::BlackDirectory::getHomeDirectoryPath() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // My home dir: /home/root
            *   // My home dir: /home/root
            * @endcode
            */
            static std::string  getHomeDirectoryPath();

            /*! @brief Exports username.
            *
            *  @return Current username which logged in to OS or empty string.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir();
            *
            *   std::cout << "My username: " << myDir.getCurrentUserName() << std::endl;
            *   std::cout << "My username: " << BlackLib::BlackDirectory::getCurrentUserName() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // My username: root
            *   // My username: root
            * @endcode
            */
            static std::string  getCurrentUserName();

            /*! @brief Exports current directory path.
            *
            *  @return Current directory path or BlackLib::CURRENT_DIRECTORY_NOT_FOUND string.
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Current dir path: " << BlackLib::BlackDirectory::getCurrentDirectoryPath() << std::endl;
            *
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *   std::cout << "Current dir path: " << myDir.getCurrentDirectoryPath() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir path: /home/root/Desktop/project1
            *   // Current dir path: /sys/class
            * @endcode
            */
            static std::string  getCurrentDirectoryPath();

            /*! @brief Exports current directory name.
            *
            *  @return Current directory name or empty string.
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Current dir name: " << BlackLib::BlackDirectory::getCurrentDirectoryName() << std::endl;
            *
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *   std::cout << "Current dir name: " << myDir.getCurrentDirectoryName() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir name: project1
            *   // Current dir name: class
            * @endcode
            */
            static std::string  getCurrentDirectoryName();

            /*! @brief Exports current directory size in bytes.
            *
            *  @return Current directory size in bytes or 0.
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Current dir size: " << BlackLib::BlackDirectory::getCurrentDirectorySize() << std::endl;
            *
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *   std::cout << "Current dir size: " << myDir.getCurrentDirectorySize() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir size: 41
            *   // Current dir size: 1
            * @endcode
            */
            static long int     getCurrentDirectorySize();

            /*! @brief Exports directory size in bytes.
            *
            *  @param [in] directoryPath    destination directory path
            *
            *  @return Specified directory size in bytes or 0.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Dir size: " << myDir.getDirectorySize("/home/root/Desktop") << std::endl;
            *   std::cout << "Dir size: " << BlackLib::BlackDirectory::getDirectorySize("/home/root/Desktop") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Dir size: 1
            *   // Dir size: 1
            * @endcode
            */
            static long int     getDirectorySize(std::string directoryPath);

            /*! @brief Checks directory existence.
            *
            *  @param [in] directoryPath    destination directory path
            *
            *  @return True if directory exists else false.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Exists?: " << std::boolalpha << myDir.exists("/home/root/Desktop") << std::endl;
            *   std::cout << "Exists?: " << std::boolalpha << BlackLib::BlackDirectory::exists("/home/root/Desktop") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Exists?: True
            *   // Exists?: True
            * @endcode
            */
            static bool         exists(std::string directoryPath);

            /*! @brief Creates new directory.
            *
            *  @param [in] directoryPath    new directory path or name
            *
            *  @return True if directory is created else false.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Created?: " << std::boolalpha << myDir.makeDirectory("/tmp/dir1") << std::endl;
            *   std::cout << "Created?: " << std::boolalpha << BlackLib::BlackDirectory::makeDirectory("/tmp/dir2") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Created?: True
            *   // Created?: True
            * @endcode
            */
            static bool         makeDirectory(std::string directoryPath);

            /*! @brief Removes directory.
            *
            *  If second parameter is set to false, this function tries to remove directory. If directory is empty,
            *  this operation will succes else fail. If second parameter is set to true, it tries to remove directory, files
            *  and subdirectories. If directory cannot be removed, it keeps going and attempts to delete as many files and
            *  sub-directories as possible.
            *
            *
            *  @param [in] directoryPath    destination directory path
            *  @param [in] rmRecursively    remove recursively
            *
            *  @return False if directory couldn't remove else true.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Removed?: " << std::boolalpha << myDir.removeDirectory("/tmp/dir1",true) << std::endl;
            *   std::cout << "Removed?: " << std::boolalpha << BlackLib::BlackDirectory::removeDirectory("/tmp/dir2") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Removed?: True
            *   // Removed?: True
            * @endcode
            */
            static bool         removeDirectory(std::string directoryPath, bool rmRecursively = false);

            /*! @brief Renames directory.
            *
            *  @param [in] oldDirectoryPath    old name of directory
            *  @param [in] newDirectoryPath    new name of directory
            *
            *  @return True if directory name is changed else false.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Renamed?: " << std::boolalpha << myDir.renameDirectory("/tmp/dir1","/tmp/dir3") << std::endl;
            *   std::cout << "Renamed?: " << std::boolalpha << BlackLib::BlackDirectory::renameDirectory("/tmp/dir2","/tmp/dir4") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Renamed?: True
            *   // Renamed?: True
            * @endcode
            */
            static bool         renameDirectory(std::string oldDirectoryPath, std::string newDirectoryPath );

            /*! @brief Changes working directory.
            *
            *  @param [in] path    destination path
            *
            *  @return True if working directory is changed else false.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Changed?: " << std::boolalpha << myDir.cd("/tmp/dir1") << std::endl;
            *   std::cout << "Current dir path: " << BlackLib::BlackDirectory::getCurrentDirectoryPath() << std::endl;
            *
            *   std::cout << "Changed?: " << std::boolalpha << BlackLib::BlackDirectory::cd("/tmp/dir2") << std::endl;
            *   std::cout << "Current dir path: " << BlackLib::BlackDirectory::getCurrentDirectoryPath() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Changed?: True
            *   // Current dir path: /tmp/dir1
            *   // Changed?: True
            *   // Current dir path: /tmp/dir2
            * @endcode
            */
            static bool         cd(std::string path);

            /*! @brief Changes working directory to up directory.
            *
            *  @return True if working directory is changed else false.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class/");
            *
            *   std::cout << "Changed?: " << std::boolalpha << myDir.cdUp() << std::endl;
            *   std::cout << "Current dir path: " << BlackLib::BlackDirectory::getCurrentDirectoryPath() << std::endl;
            *
            *   std::cout << "Changed?: " << std::boolalpha << BlackLib::BlackDirectory::cdUp() << std::endl;
            *   std::cout << "Current dir path: " << BlackLib::BlackDirectory::getCurrentDirectoryPath() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Changed?: True
            *   // Current dir path: /sys
            *   // Changed?: True
            *   // Current dir path: /
            * @endcode
            */
            static bool         cdUp();

            /*! @brief Checks working directory is root or not.
            *
            *  @return True if working directory is root else false.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/");
            *
            *   std::cout << "IsRoot?: " << std::boolalpha << myDir.isRoot() << std::endl;
            *   myDir.cdUp();
            *   std::cout << "IsRoot?: " << std::boolalpha << BlackLib::BlackDirectory::isRoot() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // IsRoot?: False
            *   // IsRoot?: True
            * @endcode
            */
            static bool         isRoot();

            /*! @brief Exports the directories, files and sybollic links list in directory.
            *
            * Users can hide or get hidden files with second paramter of function or select
            * which components are shown in output with third parameter of this function. Also
            * they can sort the output by alphabetically with forth parameter. The default values
            * of this function are "exclude hidden files", "show all files" and "sort alphabetically".
            * It does not show "." and ".." never.
            *
            *  @param [in] directoryPath        destination path
            *  @param [in] hf                   hidden files shown format
            *  @param [in] cf                   selection file formats to show
            *  @param [in] sortAlphabetically   sort alphabetically the output
            *
            *  @return The list of directory's components.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class");
            *   std::vector<std::string> ls = myDir->getEntryList("/sys",
            *                                                     BlackLib::BlackDirectory::IncludeHiddens,
            *                                                     BlackLib::BlackDirectory::All,
            *                                                     true);
            *
            *   std::cout << "Current dir path: " << myDir.getCurrentDirectoryPath() << std::endl << std::endl;
            *   std::cout << "Output of \'ls -a /sys/\' command:" << std::endl;
            *
            *   for( unsigned int i = 0 ; i <ls.size() ; i++ )
            *   {
            *       std::cout << ls[i] << std::endl;
            *   }
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir path: /sys/class
            *   //
            *   // Output of 'ls -a /sys/' command:
            *   // block
            *   // bus
            *   // class
            *   // dev
            *   // devices
            *   // firmware
            *   // fs
            *   // kernel
            *   // module
            *   // power
            * @endcode
            */
            static std::vector<std::string> getEntryList(std::string directoryPath,
                                                         BlackDirectory::hiddenFormat    hf = BlackDirectory::ExcludeHiddens,
                                                         BlackDirectory::componentFormat cf = BlackDirectory::All,
                                                         bool sortAlphabetically = true);


            /*! @brief Exports the directories, files and sybollic links count in directory.
            *
            * Users can hide or get hidden files with second paramter of function or select
            * which components are added to count with third parameter of this function. The
            * default values of this function are "exclude hidden files" and "show all files".
            * It does not add to count "." and ".." never.
            *
            *  @param [in] directoryPath        destination path
            *  @param [in] hf                   hidden files shown format
            *  @param [in] cf                   selection file formats to show
            *
            *  @return The count of directory's components.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/class");
            *
            *    std::cout << "Current dir path: " << myDir.getCurrentDirectoryPath() << std::endl << std::endl;
            *
            *   std::cout << "The directory \"/sys\" contains " << myDir->getEntryCount("/sys") << " element(s)." << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir path: /sys/class
            *   //
            *   // The directory "/sys" contains 10 element(s).
            * @endcode
            */
            static unsigned int getEntryCount(std::string directoryPath,
                                              BlackDirectory::hiddenFormat    hf = BlackDirectory::ExcludeHiddens,
                                              BlackDirectory::componentFormat cf = BlackDirectory::All);


            /*! @brief Exports the directories, files and sybollic links list in current directory.
            *
            * Users can hide or get hidden files with second paramter of function or select
            * which components are shown in output with third parameter of this function. Also
            * they can sort the output by alphabetically with forth parameter. The default values
            * of this function are "exclude hidden files", "show all files" and "sort alphabetically".
            * It does not show "." and ".." never.
            *
            *  @param [in] hf                   hidden files shown format
            *  @param [in] cf                   selection file formats to show
            *  @param [in] sortAlphabetically   sort alphabetically the output
            *
            *  @return The list of current directory's components.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys");
            *   std::vector<std::string> ls = myDir->getEntryList(BlackLib::BlackDirectory::IncludeHiddens,
            *                                                     BlackLib::BlackDirectory::All,
            *                                                     true);
            *
            *   std::cout << "Current dir path: " << myDir.getCurrentDirectoryPath() << std::endl << std::endl;
            *
            *   std::cout << "Output of \'ls -a\' command:" << std::endl;
            *   for( unsigned int i = 0 ; i <ls.size() ; i++ )
            *   {
            *       std::cout << ls[i] << std::endl;
            *   }
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir path: /sys/
            *   //
            *   // Output of 'ls -a' command:
            *   // block
            *   // bus
            *   // class
            *   // dev
            *   // devices
            *   // firmware
            *   // fs
            *   // kernel
            *   // module
            *   // power
            * @endcode
            */
            std::vector<std::string> getEntryList(BlackDirectory::hiddenFormat    hf = BlackDirectory::ExcludeHiddens,
                                                  BlackDirectory::componentFormat cf = BlackDirectory::All,
                                                  bool sortAlphabetically = true);

            /*! @brief Exports the directories, files and sybollic links count in current directory.
            *
            * Users can hide or get hidden files with second paramter of function or select
            * which components are added to count with third parameter of this function. The
            * default values of this function are "exclude hidden files" and "show all files".
            * It does not add to count "." and ".." never.
            *
            *  @param [in] hf                   hidden files shown format
            *  @param [in] cf                   selection file formats to show
            *
            *  @return The count of current directory's components.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/");
            *
            *    std::cout << "Current dir path: " << myDir.getCurrentDirectoryPath() << std::endl << std::endl;
            *
            *   std::cout << "This directory contains " << myDir->getEntryCount() << " element(s)." << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current dir path: /sys
            *   //
            *   // This directory "/sys" contains 10 element(s).
            * @endcode
            */
            unsigned int getEntryCount(BlackDirectory::hiddenFormat    hf = BlackDirectory::ExcludeHiddens,
                                       BlackDirectory::componentFormat cf = BlackDirectory::All);

            /*! @brief Exports the application directory path.
            *
            *  @return the application directory path.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/");
            *
            *    std::cout << "App dir path: " << myDir.getApplicationDirectoryPath() << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // App dir path: /home/root/Desktop/project1
            * @endcode
            */
            std::string  getApplicationDirectoryPath();

            /*! @brief Exports the application directory name.
            *
            *  @return the application directory name.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackDirectory  myDir("/sys/");
            *
            *    std::cout << "App dir name: " << myDir.getApplicationDirectoryName() << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // App dir name: project1
            * @endcode
            */
            std::string  getApplicationDirectoryName();
    };


    // ############################################ BLACKDIRECTORY DECLARATION ENDS ############################################# //


} /* namespace BlackLib */

#endif /* BLACKDIRECTORY_H_ */
