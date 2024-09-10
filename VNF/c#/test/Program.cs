using System;
using Vnf;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Test
{
    class Test
    {         
        static void Main(string[] args)
        {

            char[] dd = VNF.Decrypt("NAME.vnf");
            List<string[]> pd = VNF.Parse(dd);



            foreach (var item in pd)
            {
                foreach (var i in item)
                {
                    System.Console.WriteLine(i);
                }
            }



        }
    }
}