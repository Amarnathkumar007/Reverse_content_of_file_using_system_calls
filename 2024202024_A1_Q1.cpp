#include <cstring>      // used for strcmp
#include <cstdlib>      // used for atoi
#include <iostream>     // used for cout
#include <fcntl.h>      // used for open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC
#include <sys/stat.h>   // used for stat, mkdir
#include <unistd.h>     // used for lseek, write, read, close
#include <algorithm>
using namespace std;
/**
 * variables
 */
unsigned long long file_size;
int fd_read,fd_write;
struct stat fileStat;
unsigned long long processed=0;
/**
 * functions
 * get_path: will take string and return the name of file even if directory supplied
 * make_directory: will create directory named Assignement1
 * is_file_exist: check whether file exist or not
 * open_file: will open both file one is in read and other is in write 
 * reverse_content_parameterized: will reverse the content of file for the givne parameter
 * copy_content: will copy content of one file to another.
 */

string get_path(string path){

    string res="";
    for(int i=path.size()-1;i>=0;i--){
        if(path[i]=='/') break;
        res+=path[i];
    }   
    reverse(res.begin(),res.end());
    return res;
}

void make_directory(){
    string dir_name="Assignment1";
    int result = mkdir(dir_name.c_str(), 0744);//owner will have all r,w,x where as other will have only read permisssion
}

bool is_file_exist(const char *file_name)
{
    const char *filename = file_name;
        

        if (stat(filename, &fileStat) == 0) {
            file_size=fileStat.st_size;
            return true;
        } else {
                throw 7;
        }
        return true;
}
void open_file(string path,string output_para){
        fd_read= open(path.c_str(), O_RDONLY);

        if(fd_read==-1) 
        {
            throw 0;
        }
        string output_file="Assignment1/";
        output_file+=output_para;
        output_file+="_";
        output_file+=get_path(path);
        fd_write = open(output_file.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0744); // 0744 r,w,x for owner and r for group and other

        if(fd_write<0){
            throw 3;
        }
}
// void reverse(char *begin,char* end){
//     while(begin<end){
//         swap(*begin,*end);
//         begin+=1;
//         end-=1;
//     }

// }

void reverse_content_parameterized(unsigned long long s_index,unsigned long long e_index,unsigned long long& processed,const unsigned long long total_size)
{       
        char data[10240];
        int read_size=10240;
        unsigned long long current_reader=0;
        ssize_t bytesReader;

        while(true){
            if(read_size>e_index-s_index+1){
                lseek(fd_read, //file discriptor 
                    s_index,//offset
                    SEEK_SET //from wherer to read
                    );
                read_size= e_index-s_index+1;
                bytesReader= read(fd_read, data, read_size);
                reverse(data,data+read_size);
                ssize_t bytesWritten = write(fd_write, data, read_size);
                if (bytesWritten == -1) {throw 2;}
                processed+=read_size;
                cout << "\033[2J\033[H";

                cout<<"\tprogress: "<<(processed*100)/total_size<<"%"<<endl;
                return;
            }else{
                lseek(fd_read, //file discriptor 
                    e_index-read_size,//offset
                    SEEK_SET //from where to read
                    );
                e_index-=read_size;
                bytesReader= read(fd_read, data,read_size);
                reverse(data,data+read_size);
                ssize_t bytesWritten = write(fd_write, data, read_size);
                if (bytesWritten == -1) {throw 2;}
                
                processed+=read_size;
                cout << "\033[2J\033[H";
                cout<<"\t"<<"progress: "<<((processed*100)/total_size)<<"%"<<endl;

            }
        }
}
void copy_content(unsigned long long s_index,unsigned long long e_index,unsigned long long& processed,const unsigned long long total_size){
    cout<<"copying the content\n";
    char data[10240];
    int read_size=10240;
    ssize_t bytesReader;
    while(true){
        if(10240>e_index-s_index+1){
            lseek(fd_read, //file discriptor 
                s_index,//offset
                SEEK_SET //from where to read
                ); 

            read_size= e_index-s_index+1;
            processed+=read_size;
            bytesReader= read(fd_read, data,read_size);
            if(bytesReader==-1) throw 1;

            ssize_t bytesWritten = write(fd_write, data, read_size);
            if (bytesWritten == -1) {throw 2;}
            cout << "\033[2J\033[H";
            cout<<"\t"<<"progress: "<<((processed*100)/total_size)<<"%\t"<<endl;
            return;
        }else{
            lseek(fd_read, //file discriptor 
                s_index,//offset
                SEEK_SET //from wherer to read
            );
            s_index+=read_size;
            bytesReader= read(fd_read, data,read_size);

            ssize_t bytesWritten = write(fd_write, data, read_size);
            if (bytesWritten == -1) {throw 2;}

            processed+=read_size;
            cout<<processed<<" "<<total_size<<endl;
            cout << "\033[2J\033[H";
            cout<<"\t"<<"progress: "<<(processed*100)/total_size<<"%\t";
        }
    }
};
/**
 * In the main function we first check is file exist or not
 * Then checks the number of argments if satisfies we open file
 * if 0 we just call reverse method from start index 0 to end index -1.
 * if 1 supplied we call reverse method twice 1st we give parameter from 0 to given_index-1 and then copy content and finally again reverse content from e_index to end of file.
 * Finally at the end we close file
 */
int main(int argc, char *path[]){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << "\033[2J\033[H";
    try{
        if(!is_file_exist(path[1])){
            throw 4;
        };
        make_directory();
        
        int c=atoi(path[2]);
        if(c==0){
            if(argc!=3) throw 5;
            open_file(path[1],path[2]);
            reverse_content_parameterized(0,file_size-1,processed,file_size);

        }else{
            if((c!=1)&&(argc!=5)&&(atoi(path[4]) >=file_size || atoi(path[3])<0)){
                throw 5;
            }
            open_file(path[1],path[2]);

            unsigned long long s_index=atoi(path[3]);
            unsigned long long e_index=atoi(path[4]);

            if(s_index>file_size || e_index>file_size || s_index >= e_index){
                throw 5;
            }
            reverse_content_parameterized(0,s_index-1,processed,file_size);
            copy_content(s_index,e_index,processed,file_size);
            reverse_content_parameterized(e_index+1,file_size-1,processed,file_size);
        }
        
        close(fd_read);
        close(fd_write);

    }
    /**
     * Exceptions handled here
     * If not handled will return exception is unkown
     */
    catch(int val)
    {
        if(val==0)
            cout<<"issue in opening file";

        else if(val==1)
            cout<<"issue in reading file";

        else if(val==2)
            cout<<"error in writing";
        
        else if(val==3)
            cout<<"error in creating file or opening";

        else if(val==4)
            cout<<"error in opening file";
        else if(val==5){
            cout<<"invalid parameter";
        }
        else if(val==6){
            cout<<"error in creating directory";
        }else if(val==7){
            cout<<"file doesn't exist";
        }else{
            cout<<"Exception is unkown";
        }
    }
    catch (const exception& e) {
        cout << "Exception " << e.what() << endl;
    }catch(...){
        cout<<"Exception is unknown";
    }

    return 0;
}