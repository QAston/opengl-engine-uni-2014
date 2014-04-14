#ifndef DRAWABLE_H
#define DRAWABLE_H

// interface
class Drawable
{
    public:
        virtual ~Drawable() {}
        virtual void draw() = 0;
    protected:
    private:
};

#endif // DRAWABLE_H
