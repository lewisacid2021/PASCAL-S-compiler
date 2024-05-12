program main;
type
apple = record
    b : integer;
end;
var
  a: integer;
  b: record
   title: array [1..50] of char;
   author: array [1..50] of char;
   subject: array [1..100] of char;
   book_id: integer;
end;
begin
  a := 3;
  write(a);
end.
