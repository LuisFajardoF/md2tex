!--
    bibstyle: bwl-FU
--!
Random citation embedded[1] in text.  
This is a bibliography test[1].  
This is a bibliography test[2].  
This is a bibliography test[5].  
This is a bibliography test[3].

```bib
[1]: book {
    author:     John Doe
    title:      The Book without Title
    publisher:  Dummy Publisher
    year:       2010
}

[2]: inbook {
    author:     Indiana Jones
    title:      Los secretos de Africa
    publisher:  Holliwood Review
    year:       2015
}

[5]: inbook {
    author:     John Doe
    title:      The Book without Title
    publisher:  Dummy Publisher
    year:       2000
    pages:      100-200
}

[3]: misc {
    url:        https://intel.com
    author:     Intel
    title:      Example Website
    month:      12
    year:       1998
    note:       accessed on 2021-02-16
}
```
