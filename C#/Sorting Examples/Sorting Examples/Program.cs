using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Sort.Net;

namespace Sorting_Examples
{
    class Program
    {
        static void Main(string[] args)
        {   
            int counter = 30000;
            int[] a = random_array(counter);

            Console.WriteLine("Starting BubbleSort");
            Sort.Net.BubbleSort.sort(ref a);
            Console.WriteLine("Finished BubbleSort on {0} items\n", counter);

            a = random_array(counter);

            Console.WriteLine("Starting QuickSort");
            Sort.Net.QuickSort.sort(ref a);
            Console.WriteLine("Finished QuickSort on {0} items\n", counter);

            Console.WriteLine("Done with sorting demo.");
            Console.ReadLine();
        }
        static int[] random_array(int count)
        {
            Random r = new Random();
            int[] a = new int[count];
            for (int i = 0; i < count; i++)
            {
                a[i] = r.Next(0, int.MaxValue - 1);
            }
            return a;
        }
    }
}
