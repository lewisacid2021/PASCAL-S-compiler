program main;
var
  ret: integer;
  a: array[1..5, 1..3] of integer;
  b: array[1..5, 1..3] of integer;
  c: array[1..5, 1..3] of integer;
  d: array[1..5, 1..3] of integer;
  e: array[1..5, 1..3] of integer;
  f: array[1..5] of integer;
  g: array[1..5, 1..3] of integer;
  h: array[1..3] of integer;
  i: array[1..2, 1..3, 1..4] of integer;
begin
  ret := 0;

  a[1, 1] := 0;
  a[1, 2] := 0;
  a[1, 3] := 0;
  a[2, 1] := 0;
  a[2, 2] := 0;
  a[2, 3] := 0;
  a[3, 1] := 0;
  a[3, 2] := 0;
  a[3, 3] := 0;
  a[4, 1] := 0;
  a[4, 2] := 0;
  a[4, 3] := 0;
  a[5, 1] := 0;
  a[5, 2] := 0;
  a[5, 3] := 0;

  b[1, 1] := 0;
  b[1, 2] := 0;
  b[1, 3] := 0;
  b[2, 1] := 0;
  b[2, 2] := 0;
  b[2, 3] := 0;
  b[3, 1] := 0;
  b[3, 2] := 0;
  b[3, 3] := 0;
  b[4, 1] := 0;
  b[4, 2] := 0;
  b[4, 3] := 0;
  b[5, 1] := 0;
  b[5, 2] := 0;
  b[5, 3] := 0;

  c[1, 1] := 1;
  c[1, 2] := 2;
  c[1, 3] := 3;
  c[2, 1] := 4;
  c[2, 2] := 5;
  c[2, 3] := 6;
  c[3, 1] := 7;
  c[3, 2] := 8;
  c[3, 3] := 9;
  c[4, 1] := 10;
  c[4, 2] := 11;
  c[4, 3] := 12;
  c[5, 1] := 13;
  c[5, 2] := 14;
  c[5, 3] := 15;

  d[1, 1] := 1;
  d[1, 2] := 2;
  d[1, 3] := 3;
  d[2, 1] := 4;
  d[2, 2] := 5;
  d[2, 3] := 6;
  d[3, 1] := 7;
  d[3, 2] := 8;
  d[3, 3] := 9;
  d[4, 1] := 10;
  d[4, 2] := 11;
  d[4, 3] := 12;
  d[5, 1] := 13;
  d[5, 2] := 14;
  d[5, 3] := 15;

  e[1, 1] := 1;
  e[1, 2] := 2;
  e[1, 3] := 3;
  e[2, 1] := 4;
  e[2, 2] := 5;
  e[2, 3] := 6;
  e[3, 1] := 7;
  e[3, 2] := 8;
  e[3, 3] := 9;
  e[4, 1] := 10;
  e[4, 2] := 11;
  e[4, 3] := 12;
  e[5, 1] := 13;
  e[5, 2] := 14;
  e[5, 3] := 15;

  f[1] := 0;
  f[2] := 0;
  f[3] := 0;
  f[4] := 0;
  f[5] := 0;

  g[1, 1] := 1;
  g[1, 2] := 2;
  g[1, 3] := 3;
  g[2, 1] := 4;
  g[2, 2] := 0;
  g[2, 3] := 0;
  g[3, 1] := 7;
  g[3, 2] := 0;
  g[3, 3] := 0;
  g[4, 1] := 10;
  g[4, 2] := 11;
  g[4, 3] := 12;
  g[5, 1] := 0;
  g[5, 2] := 0;
  g[5, 3] := 0;

  h[1] := 0;
  h[2] := 0;
  h[3] := 0;

  i[1, 1, 1] := 1;
  i[1, 1, 2] := 2;
  i[1, 1, 3] := 3;
  i[1, 1, 4] := 4;
  i[1, 2, 1] := 5;
  i[1, 2, 2] := 0;
  i[1, 2, 3] := 0;
  i[1, 2, 4] := 0;
  i[2, 1, 1] := 0;
  i[2, 1, 2] := 0;
  i[2, 1, 3] := 0;
  i[2, 1, 4] := 0;
  i[2, 2, 1] := 0;
  i[2, 2, 2] := 0;
  i[2, 2, 3] := 0;
  i[2, 2, 4] := 0;
  i[2, 3, 1] := 0;
  i[2, 3, 2] := 0;
  i[2, 3, 3] := 0;
  i[2, 3, 4] := 0;

  ret := 4;

  write(ret);
end.