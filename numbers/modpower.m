function res = modpower(a, p, m);

if p == 0,
  res = ones(size(a));
elseif p == 1,
  res = mod(a, m);
else
  res = [];
  for base = a,
    res = [res mod(base * modpower(base, p - 1, m), m)];
  end;
end;
