program main;
type
    books = record
    title:integer;
end;
var b:books;
function test(a:books):integer;
begin
    test:=a.title;
end;
begin
    b.title:=1;
    write(test(b));
end.
