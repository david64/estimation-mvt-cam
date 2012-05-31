
plot3(x,y,z)
hold on
quiver3(x,y,z,I(1,:),I(2,:),I(3,:))
quiver3(x,y,z,J(1,:),J(2,:),J(3,:))
quiver3(x,y,z,K(1,:),K(2,:),K(3,:))

axis("equal")

