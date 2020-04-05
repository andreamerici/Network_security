function set = totientset(n);

set = [];

for a = 1:n,
  if(gcd(a, n) == 1),
    set = [set a];
  end;
end;
