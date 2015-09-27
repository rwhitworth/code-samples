using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace xml_test
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlTextReader reader = null;

            if (args.Length == 0)
            {
                reader = new XmlTextReader(@"wiki.xml");
            }
            else
            {
                reader = new XmlTextReader(args[0]);
            }

            bool printtitle = false;
            bool timestamp = false;
            bool redirect = false;
            bool talkpage = false;
            bool userpage = false;
            bool colon = false;
            int ns = 0;
            string title = "";
            string time = "";

            #region commented out.. while()
            //while (reader.Read())
            //{
            //    switch (reader.NodeType)
            //    {
            //        case XmlNodeType.Element: 
            //            // The node is an element.
            //            //Console.Write("<" + reader.Name);

            //            //while (reader.MoveToNextAttribute()) // Read the attributes.
            //            //    Console.Write(" " + reader.Name + "='" + reader.Value + "'");
            //            //Console.WriteLine(">");

            //            if (reader.Name == "title") { printtitle = true;  }
            //            else { printtitle = false; }
            //            if (reader.Name == "timestamp") { timestamp = true; }
            //            else { timestamp = false; }
            //            if (reader.Name == "redirect") { redirect = true; }
            //            break;
            //        case XmlNodeType.Text: 
            //            //Display the text in each element.

            //            if (!redirect)
            //            {
            //                if (printtitle) { Console.Write(reader.Value + ","); }
            //                if (timestamp) { Console.WriteLine(reader.Value); }
            //            }
            //            break;
            //        case XmlNodeType.EndElement:
            //            //Display the end of the element.
            //            //Console.Write("</" + reader.Name);
            //            //Console.WriteLine(">");
            //            if (reader.Name == "page")
            //            {
            //                printtitle = false;
            //                timestamp = false;
            //                redirect = false;
            //            }
            //            break;
            //    }
            //}

            #endregion  

            while (reader.Read())
            {

                #region Element
                if (reader.NodeType == XmlNodeType.Element)
                {
                    #region title
                    if (reader.Name == "title")
                    {
                        reader.Read();
                        if (reader.NodeType == XmlNodeType.Text)
                        {
                            title = reader.Value;
                            printtitle = true;
                            if (title.StartsWith("Talk:")) { talkpage = true; }
                            if (title.StartsWith("User:")) { userpage = true; }
                        }
                    }
                    #endregion
                    #region timestamp
                    if (reader.Name == "timestamp")
                    {
                        reader.Read();
                        if (reader.NodeType == XmlNodeType.Text)
                        {
                            time = reader.Value;
                            timestamp = true;
                        }
                    }
                    #endregion
                    #region redirect
                    if (reader.Name == "redirect")
                    {
                        redirect = true;
                    }
                    #endregion
                    #region ns
                    if (reader.Name == "ns")
                    {
                        reader.Read();
                        if (reader.NodeType == XmlNodeType.Text)
                        {
                            try
                            {
                                ns = int.Parse(reader.Value);
                            }
                            catch (Exception)
                            {
                                // assume we can't print this item
                                ns = 1;
                            }
                        }
                    }
                    #endregion  
                    continue;
                }
                #endregion

                #region EndElement
                if ((reader.NodeType == XmlNodeType.EndElement) && (reader.Name == "page"))
                {
                    if ((!redirect) && (!talkpage) && (!userpage) && (ns == 0))
                    {
                        if (title.Contains(","))
                        {
                            title = "\"" + title + "\"";
                        }
                        Console.WriteLine("{0},{1}", title, time);
                    }

                    #region reset variables
                    timestamp = false;
                    printtitle = false;
                    redirect = false;
                    talkpage = false;
                    userpage = false;
                    ns = 0;
                    #endregion  
                }
                #endregion  

            }

            //Console.ReadLine();
        }
    }
}
