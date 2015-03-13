using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sort.Net
{
    public class BubbleSort
    {
        public static void sort(ref int[] unsorted)
        {
            int len = unsorted.Length;
            int toolarge = 50000;
            if (len > toolarge)
            {
                // BubbleSort takes far too long to process 50000 items on even a moderatly fast Intel Core i7 processor
                throw new Exception(String.Format("BubbleSort should not be used with greater than {0} items", toolarge));
            }
            while (!Sort.Net.Util.isSorted(ref unsorted))
            {
                for (int i = 1; i < len; i++)
                {
                    if (unsorted[i - 1] > unsorted[i])
                    {
                        Sort.Net.Util.swap(ref unsorted, i - 1, i);
                    }
                }
            }
        }
    }
}
