/*
 * BlackDirectory.cpp
 *
 *  Created on: 21 Eki 2014
 *      Author: yigityuce
 */

#include "BlackDirectory.h"

namespace BlackLib
{

    BlackDirectory::BlackDirectory()
    {
        this->applicationDirectory = BlackDirectory::getCurrentDirectoryPath();
    }

    BlackDirectory::BlackDirectory(std::string path)
    {
        this->applicationDirectory  = BlackDirectory::getCurrentDirectoryPath();
        BlackDirectory::cd(path);
    }

    BlackDirectory::~BlackDirectory()
    {

    }


    std::string BlackDirectory::getHomeDirectoryPath()
    {
        passwd *pw = getpwuid(getuid());
        std::string homeDir( pw ? pw->pw_dir : "");

        return homeDir;
    }

    std::string BlackDirectory::getCurrentUserName()
    {
        passwd *pw = getpwuid(getuid());
        std::string username( pw ? pw->pw_name : "");

        return username;
    }

    std::string BlackDirectory::getCurrentDirectoryPath()
    {
        std::string pwd;
        pwd.resize(1000,'\t');

        bool isFound = ( getcwd(&(pwd[0]), pwd.size()) != NULL );


        if ( isFound )
        {
            size_t first = pwd.find_first_of('\t',0);
            pwd.resize(first);
        }
        else
        {
            pwd = BlackLib::CURRENT_DIRECTORY_NOT_FOUND;
        }

        return pwd;

    }

    std::string BlackDirectory::getCurrentDirectoryName()
    {
        std::string pwd     = BlackDirectory::getCurrentDirectoryPath();
        std::string dirName = "";

        if( pwd != BlackLib::CURRENT_DIRECTORY_NOT_FOUND and pwd != "/" )
        {
            if( pwd[pwd.size()-1] == '/' ) { pwd.resize(pwd.size()-1); }

            dirName = pwd.substr(pwd.find_last_of('/')+1);
        }

        return dirName;

    }



    long int    BlackDirectory::getCurrentDirectorySize()
    {
        return BlackDirectory::getDirectorySize(BlackDirectory::getCurrentDirectoryPath());
    }


    long int    BlackDirectory::getDirectorySize(std::string directoryPath)
    {
        struct stat sb;
        if ( stat(&directoryPath[0],&sb) == 0 )
        {
            return sb.st_size;
        }
        return 0;
    }

    bool        BlackDirectory::exists(std::string directoryPath)
    {
        struct stat sb;
        return ( stat(&directoryPath[0],&sb) == 0 );
    }











    bool BlackDirectory::cd(std::string path)
    {
        if ( BlackDirectory::exists(path) )
        {
            return (chdir(&path[0]) == 0);
        }
        return false;
    }

    bool BlackDirectory::cdUp()
    {
        return BlackDirectory::cd("..");
    }

    bool BlackDirectory::isRoot()
    {
        return (BlackDirectory::getCurrentDirectoryPath() == "/" );
    }





    std::vector<std::string> BlackDirectory::getEntryList(std::string directoryPath, BlackDirectory::hiddenFormat hf, BlackDirectory::componentFormat cf, bool sortAlphabetically)
    {
        std::vector<std::string> directoryList;
        directoryList.clear();

        if ( BlackDirectory::exists(directoryPath) )
        {
            DIR     *dp;
            dirent  *dirp;

            if( (dp = opendir(directoryPath.c_str())) != NULL)
            {
                while( (dirp = readdir(dp)) != NULL )
                {
                    std::string fname(dirp->d_name);

                    if( fname == "." ) continue;
                    if( fname == ".." ) continue;
                    if( hf == BlackDirectory::ExcludeHiddens and fname[0] == '.' ) continue;


                    struct stat sb;
                    if( stat(&fname[0],&sb) == 0 )
                    {
                        if( (cf & BlackDirectory::Directory)    == BlackDirectory::Directory    and S_ISDIR(sb.st_mode)) { directoryList.push_back(fname); }
                        if( (cf & BlackDirectory::File)         == BlackDirectory::File         and S_ISREG(sb.st_mode)) { directoryList.push_back(fname); }
                        if( (cf & BlackDirectory::SymbolicLink) == BlackDirectory::SymbolicLink and S_ISLNK(sb.st_mode)) { directoryList.push_back(fname); }
                    }

                }
                closedir(dp);
            }
        }

        if ( sortAlphabetically ) { std::sort(directoryList.begin(), directoryList.end()); }
        return directoryList;
    }

    unsigned int BlackDirectory::getEntryCount(std::string directoryPath, BlackDirectory::hiddenFormat hf, BlackDirectory::componentFormat cf)
    {
        return BlackDirectory::getEntryList(directoryPath,hf,cf,false).size();
    }


    std::vector<std::string> BlackDirectory::getEntryList(BlackDirectory::hiddenFormat hf, BlackDirectory::componentFormat cf, bool sortAlphabetically)
    {
        return BlackDirectory::getEntryList(BlackDirectory::getCurrentDirectoryPath(),hf,cf,sortAlphabetically);
    }

    unsigned int BlackDirectory::getEntryCount(BlackDirectory::hiddenFormat hf, BlackDirectory::componentFormat cf)
    {
        return BlackDirectory::getEntryList(BlackDirectory::getCurrentDirectoryPath(),hf,cf,false).size();
    }




    std::string BlackDirectory::getApplicationDirectoryPath()
    {
        return this->applicationDirectory;
    }

    std::string BlackDirectory::getApplicationDirectoryName()
    {
        std::string pwd     = this->applicationDirectory;
        std::string dirName = "";

        if( pwd != BlackLib::CURRENT_DIRECTORY_NOT_FOUND and pwd != "/" )
        {
            if( pwd[pwd.size()-1] == '/' ) { pwd.resize(pwd.size()-1); }

            dirName = pwd.substr(pwd.find_last_of('/')+1);
        }

        return dirName;
    }




    bool        BlackDirectory::makeDirectory(std::string directoryPath)
    {
        if( ! BlackDirectory::exists(directoryPath) )
        {
            return ( mkdir(&directoryPath[0], 0777) == 0);
        }

        return true;
    }

    bool        BlackDirectory::removeDirectory(std::string directoryPath, bool rmRecursively)
    {
        struct stat sb;

        if( stat(&directoryPath[0],&sb) == 0 )
        {
            if( !rmRecursively ){ return (rmdir(directoryPath.c_str()) == 0); }


            if( S_ISDIR(sb.st_mode) )
            {
                std::vector<std::string> directoryList;
                directoryList.clear();
                DIR     *dp;
                dirent  *dirp;

                if( (dp = opendir(directoryPath.c_str())) != NULL)
                {
                    while( (dirp = readdir(dp)) != NULL )
                    {
                        std::string fname(dirp->d_name);

                        if( fname == "." ) continue;
                        if( fname == ".." ) continue;
                        directoryList.push_back(fname);
                    }
                    closedir(dp);
                }

                if( directoryList.empty() )
                {
                    return (std::remove(directoryPath.c_str()) == 0);
                }

                for( unsigned int i = 0 ; i<directoryList.size() ; i++ )
                {
                    std::string fullPath = directoryPath + ((directoryPath[directoryPath.size()-1] == '/') ? directoryList[i] : "/" + directoryList[i]);
                    BlackDirectory::removeDirectory(fullPath,true);
                }

                return (std::remove(directoryPath.c_str()) == 0);
            }
            else
            {
                return (std::remove(directoryPath.c_str()) == 0);
            }
        }

        return true;
    }

    bool        BlackDirectory::renameDirectory(std::string oldDirectoryPath, std::string newDirectoryPath )
    {
        return (rename(oldDirectoryPath.c_str(),newDirectoryPath.c_str()) == 0);
    }


} /* namespace BlackLib */
