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


#ifndef EXAMPLE_DIRECTORY_H_
#define EXAMPLE_DIRECTORY_H_

#include "../BlackDirectory/BlackDirectory.h"
#include <string>
#include <iostream>






void example_directory()
{
    std::cout << "Current Directory Path: " << BlackLib::BlackDirectory::getCurrentDirectoryPath() << std::endl;
    std::cout << "Home Directory Path   : " << BlackLib::BlackDirectory::getHomeDirectoryPath() << std::endl;
    std::cout << "Current User Name     : " << BlackLib::BlackDirectory::getCurrentUserName() << std::endl;



    BlackLib::BlackDirectory *myDir = new BlackLib::BlackDirectory("/home/root/Desktop/");

    std::cout << "Application Directory Path: " << myDir->getApplicationDirectoryPath() << std::endl;
    std::cout << "Application Directory Name: " << myDir->getApplicationDirectoryName() << std::endl;
    std::cout << "Current Directory Path    : " << myDir->getCurrentDirectoryPath() << std::endl;
    std::cout << "Current Directory Name    : " << myDir->getCurrentDirectoryName() << std::endl;



    myDir->cd("/home/");
    std::cout << "Current Directory Path: " << myDir->getCurrentDirectoryPath() << std::endl;



    myDir->cdUp();
    std::cout << "Current Directory Path: " << myDir->getCurrentDirectoryPath() << std::endl;



    myDir->cd("/home/root");
    std::cout << "Current Directory Path: " << myDir->getCurrentDirectoryPath() << std::endl;



    // create file tree
    // |->dir1
    //      |->dir1
    //      |->dir2
    //      |->dir3
    //          |->dir1
    //          |->dir2
    //      |->dir4
    // |->dir2
    // |->dir3
    // |->dir4
    myDir->makeDirectory("dir1");
    myDir->makeDirectory("dir1/dir1");
    myDir->makeDirectory("dir1/dir2");
    myDir->makeDirectory("dir1/dir3");
    myDir->makeDirectory("dir1/dir3/dir1");
    myDir->makeDirectory("dir1/dir3/dir2");
    myDir->makeDirectory("dir1/dir4");
    myDir->makeDirectory("dir2");
    myDir->makeDirectory("dir3");
    myDir->makeDirectory("dir4");


    std::vector<std::string> ls = myDir->getEntryList(BlackLib::BlackDirectory::IncludeHiddens,
                                                      BlackLib::BlackDirectory::Directory,
                                                      true);


    std::cout << "\n\nls after mkdir: " << std::endl;
    for( unsigned int i = 0 ; i <ls.size() ; i++ )
    {
        std::cout << i+1 << ". entry: " << ls[i] << std::endl;
    }


    // dir1 and its subdirectories are remove recursively
    myDir->removeDirectory("dir1",true);
    myDir->removeDirectory("dir2");
    myDir->removeDirectory("dir3");



    ls = myDir->getEntryList(BlackLib::BlackDirectory::IncludeHiddens,
                             BlackLib::BlackDirectory::Directory,
                             true);


    std::cout << "\n\nls after rmdir: " << std::endl;
    for( unsigned int i = 0 ; i <ls.size() ; i++ )
    {
        std::cout << i+1 << ". entry: " << ls[i] << std::endl;
    }


    if( myDir->exists("dir4") )
    {
        myDir->renameDirectory("dir4","dir1");
    }

}



#endif /* EXAMPLE_DIRECTORY_H_ */
