using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sort.Net
{
    public class QuickSort
    {
        public static void sort(ref int[] unsorted)
        {
            int len = unsorted.Length;
            quicksort(ref unsorted, 0, len-1);
        }

        private static void quicksort(ref int[] unsorted, int low, int high)
        {
            int part = 0;

            if (low < high)
            {
                part = partition(unsorted, low, high);
                quicksort(ref unsorted, low, part - 1);
                quicksort(ref unsorted, part + 1, high);
            }
        }

        private static int partition(int[] unsorted, int low, int high)
        {
            int pivot = unsorted[high];
            int newlow = low - 1;

            for (int i = low; i < high; i++)
            {
                if (unsorted[i] <= pivot)
                {
                    newlow++;
                    Sort.Net.Util.swap(ref unsorted, newlow, i);
                }
            }
            Sort.Net.Util.swap(ref unsorted, newlow + 1, high);
            return newlow + 1;
        }
    }
}
