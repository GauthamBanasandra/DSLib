package Lib.SegmentTree;

public class Response<T> {
    public Response(boolean isValid, T data) {
        this.isValid = isValid;
        this.data = data;
    }

    public boolean isValid;
    public T data;
}
