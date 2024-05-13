program main;
function test(a:array [0..3,0..10] OF integer):integer;
begin
    a[0][0]:=a[0][1];
    write(a[0][2]);
    test:=1;
end;
begin
end.
