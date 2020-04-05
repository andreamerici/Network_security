function C = myfindinverse(b, m);
    A = [1 0 m];
    B = [0 1 b];
    while 1,
        if B(3) == 0,
            C = [A(3) -1];
            break;
        end
        if B(3) == 1,
            if B(2) < 0,
                B(2) = B(2) + m;
            end;
            C = [B(3) B(2)];
            break;
        end
        Q = floor (A(3) / B(3));
        A = A - Q * B;
        [A, B] = deal(B, A);
    end
end