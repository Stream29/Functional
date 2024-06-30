package functional;

import java.util.function.Consumer;
import java.util.function.Function;

public interface FieldFunc<Self extends FieldFunc<Self>>
{
    public default Self also(Consumer<Self> block)
    {
        block.accept((Self) this);
        return (Self) this;
    }

    public default <R> R let(Function<Self, R> block)
    {
        return block.apply((Self) this);
    }

    public default Self apply(Consumer<Self> block)
    {
        block.accept((Self) this);
        return (Self) this;
    }

}
