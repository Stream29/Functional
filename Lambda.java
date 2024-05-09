import java.util.concurrent.atomic.AtomicInteger;

@FunctionalInterface
interface Func
{
    Func call(Func args);
}

public class Lambda
{
    public static void main(String[] args)
    {
        Func one = args1 -> args2 -> args1.call(args2);
        //one = λx.λy.xy
        Func next = n -> f -> x -> f.call(n.call(f).call(x));
        //next = λn.λx.λy.x(ny)
        Func multiply = a -> b -> f -> a.call(b.call(f));
        //multiply = λa.λb.λc.a(bc)
        Func two = next.call(one);
        //two = λa.λb.a(ab)
        Func three = next.call(two);
        Func five = two.call(next).call(three);
        Func ten = multiply.call(two).call(five);

        Func y1 = a -> b -> a.call(b.call(b));
        Func y = a -> y1.call(a).call(y1.call(a));
        //Y = (λy. (λx.y(xx))(λx.y(xx)) )

        Func test = args1 ->
        {
            System.out.println("test");
            return args1;
        };

        Func printChurch = n ->
        {
            AtomicInteger count = new AtomicInteger(0);
            Func acc = x ->
            {
                count.addAndGet(1);
                return x;
            };
            n.call(acc).call(acc);
            System.out.println(count.intValue());
            return n;
        };

        AtomicInteger counter = new AtomicInteger(0);
        Func recursive = n ->
        {
            if(counter.intValue() < 25)
            {
                counter.addAndGet(1);

            }
            return n;
        };


        y.call(recursive);
    }
}