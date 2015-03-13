using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sort.Net
{
    public class Util
    {
        public static Boolean isSorted(ref int[] a)
        {
            if (a == null)
            {
                throw new Exception("Null (empty) array passed to Sort.Net.Util.isSorted");
            }
            if (a.Length < 1)
            {
                throw new Exception("Empty array passed to Sort.Net.Util.isSorted");
            }
            if (a.Length == 1)
            {
                return true;
            }
            for (int i = 1; i < a.Length; i++)
            {
                if (a[i] < a[i - 1])
                {
                    return false;
                }
            }
            return true;
        }
        public static Boolean swap(ref int[] a, Int32 first, Int32 second)
        {
            if ((a.Length < first) || (a.Length < second))
            {
                throw new Exception("Int out of bounds to Sort.Net.Util.swap");
            }
            if (a.Length < 2)
            {
                throw new Exception("a.Length < 2 to Sort.Net.Util.swap");
            }
            // QuickSort has the habit of requesting an item be swapped with itself
            // Fixing QuickSort slows the algorithm down, whereas fixing swap speeds things up overall
            // at the expense of less "error" checking
            //if (first == second)
            //{
            //    throw new Exception("first == second to Sort.Net.Util.swap");
            //}
            int temp = a[first];
            a[first] = a[second];
            a[second] = temp;

            return true;
        }
    }
}
