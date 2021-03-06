#include "edge.hpp"

namespace ps {

Edge::Edge()
{
}

Edge::Edge(QPoint p, Direction dir)
	: start_(p)
	, direction_(dir)
{
}

QPoint Edge::start() const
{
	return start_;
}

void Edge::setStart(QPoint p)
{
	start_ = p;
}

QPoint Edge::end() const
{
	return dirToPoint(direction()) + start_;
}

void Edge::setEnd(QPoint p)
{
	setStart(dirToPoint(opposite(direction())) + p);
}

Direction Edge::direction() const
{
	return direction_;
}

void Edge::setDirection(Direction dir)
{
	direction_ = dir;
}

void Edge::normalize()
{
	quint8 dirAsInt = static_cast<quint8>(direction());
	if (dirAsInt >= 4) {
		setStart(end());
		setDirection(opposite(direction()));
	}
}

Edge Edge::normalized() const
{
	Edge edge{*this};
	edge.normalize();
	return edge;
}

bool Edge::operator==(const Edge& edge) const
{
	Edge a{normalized()};
	Edge b{edge.normalized()};
	return a.start() == b.start() && a.direction() == b.direction();
}

bool Edge::operator!=(const Edge& edge) const
{
	return !(*this == edge);
}

QDataStream& operator<<(QDataStream& stream, Edge edge)
{
	return stream << edge.start_ << edge.direction_;
}

QDataStream& operator>>(QDataStream& stream, Edge& edge)
{
	return stream >> edge.start_ >> edge.direction_;
}

} // namespace ps
