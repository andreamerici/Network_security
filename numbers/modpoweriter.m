function res = modpower(a, p, m);

if p == 0,
  res = ones(size(a));
elseif p == 1,
  res = mod(a, m);
else
  res = [];
  for base = a,
    tmp = 1; for kk = 1:p, tmp = mod(tmp * base, m); end;
    res = [res tmp];
  end;
end;
