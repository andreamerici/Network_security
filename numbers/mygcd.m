% euclide algorithm
function d = mygcd(x, y);
    data = [x y];
    while 1,
        if data(1) > data(2),
            data = fliplr(data);
        end;
        if data(1) == 0,
            d = data(2);
            break;
        end;
        data(2) = mod(data(2), data(1));
    end
end