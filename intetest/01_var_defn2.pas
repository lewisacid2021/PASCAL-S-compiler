{test domain of global var define and local define}
program man;
var
  a, b: integer;
begin
  a := 3;
  b := 5;
  a := 5;
  write(a + b);
end.
