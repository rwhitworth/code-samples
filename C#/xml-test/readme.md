# Parsing XML dump from Wikipedia

Example C# code showing parsing of XML from a Wikipedia backup/dump.  The XML files can be obtained from https://en.wikipedia.org/wiki/Wikipedia:Database_download (or, https://dumps.wikimedia.org/enwiki/).  Download the 'pages-meta-current' file(s) and use bzip2 to uncompress.

Output contains the article title and last edit date.  Talk and user pages are ignored.  Redirect pages containing no content are ignored.

In order to process all articles on Wikipedia you will need to download ALL (roughly 27) bzip2 files and use this tool on them.

Processing a single gigabyte of XML with this tool takes roughly 7 seconds.
