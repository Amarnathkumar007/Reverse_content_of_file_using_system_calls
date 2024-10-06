#include <fcntl.h>      //function used open, lseek, O_RDONLY
#include <cstring>      // used for memcmp
#include <sys/stat.h>   // used for stat
#include <iostream>     //used function cout
#include <unistd.h>     // used for write, read, close
#include <algorithm>

using namespace std;
/**
 * variables
 */
unsigned long long file_size1,file_size2;
int fd_read1,fd_read2;
struct stat fileStat1,fileStat2,dirStat;
unsigned long long processed=0;

/**
 * functions
 */

bool is_file_exist(const char *file_name1,const char *file_name2,const char *Dir_path)
{
        if ((stat(file_name1, &fileStat1) == 0) && (stat(file_name2,&fileStat2)==0) &&
        stat(Dir_path,&dirStat)==0) {
            if (!S_ISREG(fileStat1.st_mode)) throw 4;
            if (!S_ISREG(fileStat2.st_mode)) throw 4;
            if (!S_ISDIR(dirStat.st_mode)) throw 5;

            file_size1=fileStat1.st_size;
            file_size2=fileStat2.st_size;

            return true;
        } else {throw 1;}
}

bool check_conetent_reversed(){
    unsigned long long  s_index1=0,
                        e_index1=file_size1-1,
                        s_index2=0,
                        e_index2=file_size2-1;

    char data1[10240];
    char data2[10240];

    int read_size=10240;
    ssize_t bytesReader;

    while(true){
        if(read_size>e_index1-s_index1+1){
            lseek(fd_read1, //file discriptor 
                s_index1,//offset
                SEEK_SET //from wherer to read
                );
            read_size= e_index1-s_index1+1;
            bytesReader= read(fd_read1, data1, read_size);

            reverse(data1,data1+read_size);//change

            lseek(fd_read2, //file discriptor 
                s_index2,//offset
                SEEK_SET //from wherer to read
                );
            bytesReader = read(fd_read2, data2, read_size);

            if (bytesReader == -1) {throw 2;}
            if(memcmp(data1,data2,bytesReader)!=0) {return false;}
            
            return true;
        }else{
            lseek(fd_read1, //file discriptor 
                e_index1-read_size,//offset
                SEEK_SET //from where to read
                );
            e_index1-=read_size;
            bytesReader= read(fd_read1, data1,read_size);
            reverse(data1,data1+bytesReader);

            lseek(fd_read2, //file discriptor 
                s_index2,//offset
                SEEK_SET //from wherer to read
                );
            s_index2+=read_size;
            bytesReader = read(fd_read2, data2, read_size);

            if(memcmp(data1,data2,bytesReader)!=0) false;
        }                
    }
    return true;
}

bool check_size(){
    if(file_size1==file_size2) return true;
    else return false;
}

void check_permission(){

        if(fileStat1.st_mode & S_IRUSR) cout<<"User has read permission on newFile: Yes\n";
        else cout<<"User has read permission on newFile: No\n";

        if(fileStat1.st_mode & S_IWUSR) cout<<"User has write permission on newFile: Yes\n";
        else cout<<"User has write permission on newFile: No\n";

        if(fileStat1.st_mode & S_IXUSR) cout<<"User has execute permission on newFile: Yes\n";
        else cout<<"User has execute permission on newFile: No\n";


        if(fileStat1.st_mode & S_IRGRP) cout<<"Group has read permission on newFile: Yes\n";
        else cout<<"Group has read permission on newFile: No\n";
    
        if(fileStat1.st_mode & S_IWGRP) cout<<"Group has write permission on newFile: Yes\n";
        else cout<<"Group has write permission on newFile: No\n";

        if(fileStat1.st_mode & S_IXGRP) cout<<"Group has execute permission on newFile: Yes\n";
        else cout<<"Group has execute permission on newFile: No\n";


        if(fileStat1.st_mode & S_IROTH) cout<<"Others has read permission on newFile: Yes\n";
        else cout<<"Others has read permission on newFile: No\n";
        
        if(fileStat1.st_mode & S_IWOTH) cout<<"Others has write permission on newFile: Yes\n";
        else cout<<"Others has read permission on newFile: No\n";

        if(fileStat1.st_mode & S_IXOTH) cout<<"Others has execute permission on newFile: Yes\n";
        else cout<<"Others has execute permission on newFile: No\n";
        
        
        //for old file
        if(fileStat2.st_mode & S_IRUSR) cout<<"User has read permission on old file: Yes\n";
        else cout<<"User has read permissiold file: No\n";

        if(fileStat2.st_mode & S_IWUSR) cout<<"User has write permission on old file: Yes\n";
        else cout<<"User has write permission on old file: No\n";

        if(fileStat2.st_mode & S_IXUSR) cout<<"User has execute permission on old file: Yes\n";
        else cout<<"User has execute permission on old file: No\n";


        if(fileStat2.st_mode & S_IRGRP) cout<<"Group has read permission on old file: Yes\n";
        else cout<<"Group has read permission on old file: No\n";
    
        if(fileStat2.st_mode & S_IWGRP) cout<<"Group has write permission on nold file: Yes\n";
        else cout<<"Group has write permission on old file: No\n";

        if(fileStat2.st_mode & S_IXGRP) cout<<"Group has execute permission on nold file: Yes\n";
        else cout<<"Group has execute permission on old file: No\n";


        if(fileStat2.st_mode & S_IROTH) cout<<"Others has read permission on old file: Yes\n";
        else cout<<"Others has read permission on old file: No\n";
        
        if(fileStat2.st_mode & S_IWOTH) cout<<"Others has write permission on old file: Yes\n";
        else cout<<"Others has read permission on old file: No\n";

        if(fileStat2.st_mode & S_IXOTH) cout<<"Others has execute permission on old file: Yes\n";
        else cout<<"Others has execute permission on old file: No\n";
        //Diretory

        if(dirStat.st_mode & S_IRUSR) cout<<"User has read permission on Directory: Yes\n";
        else cout<<"User has read permission on Directory: No\n";

        if(dirStat.st_mode & S_IWUSR) cout<<"User has write permission on Directory: Yes\n";
        else cout<<"User has write permission on Directory: No\n";

        if(dirStat.st_mode & S_IXUSR) cout<<"User has execute permission on Directory: Yes\n";
        else cout<<"User has execute permission on Directory: No\n";


        if(dirStat.st_mode & S_IRGRP) cout<<"Group has read permission on Directory: Yes\n";
        else cout<<"Group has read permission on Directory: No\n";
    
        if(dirStat.st_mode & S_IWGRP) cout<<"Group has write permission on Directory: Yes\n";
        else cout<<"Group has write permission on Directory: No\n";

        if(dirStat.st_mode & S_IXGRP) cout<<"Group has execute permission on Directory: Yes\n";
        else cout<<"Group has execute permission on Directory: No\n";


        if(dirStat.st_mode & S_IROTH) cout<<"Others has read permission on Directory: Yes\n";
        else cout<<"Others has read permission on Directory: No\n";
        
        if(dirStat.st_mode & S_IWOTH) cout<<"Others has write permission on Directory: Yes\n";
        else cout<<"Others has read permission on Directory: No\n";

        if(dirStat.st_mode & S_IXOTH) cout<<"Others has execute permission on Directory: Yes\n";
        else cout<<"Others has execute permission on Directory: No\n";

}
void open_file(string file1,string file2){
        fd_read1= open(file1.c_str(), O_RDONLY);
        fd_read2= open(file2.c_str(), O_RDONLY);
        if(fd_read1==-1 || fd_read2==-1) throw 2;
}

int main(int argc, char *path[]){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout.tie(NULL);
    try{
        if(argc!=4){throw 0;}
        cout << "\033[2J\033[H";

        if(!is_file_exist(path[1],path[2],path[3])){throw 1;}
        else{
            cout<<"Directory is created: Yes\n";
        }
        
        open_file(path[1],path[2]);
        
        if(check_size()){
            if(check_conetent_reversed()) cout<<"Whether content reversed: Yes\n";
            else cout<<"Whether content reversed: No\n"; 
        }else{
            cout<<"Whether content reversed: No\n";
        }

        if(check_size()){
            cout<<"Both file size are same: Yes\n";
        }else{
            cout<<"Both file size are same: No\n";

        };
        cout<<"\n\n\n";
        check_permission();
    }catch(int value){
        if(value==0) cout<<"Parameter issue please check paramenters\n";
        else if(value==1)cout<<"Please check whether file exist or not\n";
        else if(value==2) cout<<"error in opening";
        else if(value =3) cout<<"error in checking file stats";
        else if(value==4) cout<<"given paramter for file not belongs to file;\n";
        else if(value==5) cout<<"given parameter for directory doesn't belongs to directory\n";
        else cout<<"exception not handled\n";
    }catch (const exception& e) {cout << "Exception " << e.what() << endl;}
    catch(...){cout<<"something went wrong";}
    return 0;
}