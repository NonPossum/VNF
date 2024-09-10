using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace Vnf
{
    public class VNF
    {

        static void Main(string[] args)
        {

            if (args.Length == 0)
            {
                Console.WriteLine("usage:dotnet run <FileName>");
                Environment.Exit(1);
            }

 
            char[] DecryptedData = Decrypt(args[0]);
            List<string[]> ParsedData = Parse(DecryptedData);
 

            foreach (var item in ParsedData)
            {
                foreach (var i in item)
                {
                    System.Console.WriteLine(i);
                    
                }
                
            }

        
        }




        public static char[] Decrypt(string argv){
           byte[] validHeader = {0x56,0x4E,0x46};

           List<int> data = new List<int>();

           int[] key = new int[11];



           FileStream file = File.Open(argv, FileMode.Open, FileAccess.Read, FileShare.None);
           file.Seek(1,SeekOrigin.Begin);

           char[] DecryptedData = new char[file.Length - 21];

           foreach (var item in validHeader)
           {
               if(file.ReadByte() != item){
                   throw new Exception("Not a vnf file.");
               }
           }
          file.Seek(10,SeekOrigin.Begin); // Start of data section
          while(file.Position != file.Length -11)
          { 
             data.Add(file.ReadByte());
          }

          int itrr = 0;
          file.Seek(-11,SeekOrigin.End); // Start of key section
          while(file.Position != file.Length)
          {
             key[itrr] = file.ReadByte();
             itrr++;
          }

          
           file.Close();

           int itr = 0;
           int toelev = 0;
           foreach (var item in data)
           {
                 DecryptedData[itr++] =  (char)(Math.Abs(12- item) ^ key[toelev = (toelev % 11)]);
                 toelev++;

               
           }
                               
 
            return DecryptedData;
        } 


        public static List<string[]> Parse(char[] data){
            string[] split_string  = {};
            String Sdata = new String(data);            

            split_string = Sdata.Split((char)0x1D);
            split_string = split_string.Skip(1).ToArray();
   
            List<string[]> ParsedData = new List<string[]>();
            string[] name = new string[split_string.Length];
            string[] status = new string[split_string.Length];
            string[] text = new string[split_string.Length];

            

            
          uint i = 0;
          string temp = "";
          
          while(i < split_string.Length)
          {
              status[i] += split_string[i][0];
              
              string d  = split_string[i][1..^0];
              
              int j = 0;

              while(j < name.Length)
              {
                  if(d[j] != '[')
                  {
                      name[i] += d[j];
                      
                  }
                  else{
                      break;
                  }
                  j++;
              }
              

              int c = j + 1;
              while(c < d.Length)
              {
                  if(d[c] != ']'){
                      temp += d[c];
                  }
                  else{
                      text[i] = temp;
                      temp = "";
                      break;
                  }
                  c++;
              }
            
              
              i++;
          }

          ParsedData.Add(status);
          ParsedData.Add(name);
          ParsedData.Add(text);
              
       

            return ParsedData;
        } 

        
    }
}
