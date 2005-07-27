declare function listfiles( what as string, dr as string )
open "out.txt" for output as #1
open "uout.txt" for output as #2
listfiles "*.*", ""
close #1
close #2
sleep

function listfiles( what as string, dr as string )
    a$ = dir$( dr + what, &h1 )
    if a$ <> "" then print #1, left$( "  SetOutPath ""$INSTDIR\"+dr+"""", len( "  SetOutPath ""$INSTDIR\"+dr ) - 1 ) + """"
    while a$ <> ""
        print #1, "  File " + dr + a$
        print #2, "  Delete ""$INSTDIR\"+dr+a$+""""
        a$ = dir$( )
    wend
    a$ = dir$( dr + what, &h10 )
    a$ = dir$( )
    a$ = dir$( )
    i = 2
    while a$ <> ""
        i += 1
        listfiles "*.*", dr+a$+"\"
        a$ = dir$( dr + what, &h10 )
        for j = 1 to i
            a$ = dir$( )
        next
    wend
    print #2, left$( "  RMDir ""$INSTDIR\"+dr, len( "  RMDir ""$INSTDIR\"+dr ) - 1 ) + """"
end function
